#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.fmx"

TForm1 *Form1;

// Global constant
const double MillisecondsPerDay = 86400000.0;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    // Set form size on launch
    this->Width = 650;  // Set desired width
	this->Height = 450;  // Set desired height

    ReminderTimer->Enabled = false;

    // Initialize styling and tasks list box
    ApplyModernStyling();
    InitializeTasksListBox();

    // Initialize SelectedTask as nullptr
    SelectedTask = nullptr;

    // Set today's date and time in the reminder fields
    ReminderDate->Date = Now();  // Set current date
    ReminderTime->Time = Now();  // Set current time

    // Create and initialize the Delete button
    DeleteBtn = new TButton(this);
    DeleteBtn->Parent = this;
    DeleteBtn->Text = "DELETE";
	DeleteBtn->Position->X = 263; // Adjust position as needed
	DeleteBtn->Position->Y = 255;
	DeleteBtn->Width = 92;
	DeleteBtn->Height = 40;
    DeleteBtn->OnClick = DeleteBtnClick; // Attach event handler
    DeleteBtn->StyledSettings = DeleteBtn->StyledSettings >> TStyledSetting::Other;
    DeleteBtn->TextSettings->FontColor = TAlphaColorRec::White;
    DeleteBtn->StyleLookup = "buttonstyle"; // Pre-defined button style
}

//---------------------------------------------------------------------------
// Apply modern blue gradient styling to components
void TForm1::ApplyModernStyling()
{
    // Set a pastel periwinkle gradient background for the form
    this->Fill->Kind = TBrushKind::Gradient;
    this->Fill->Gradient->Color = (TAlphaColor)0xFFC3CDE6;  // Light periwinkle
    this->Fill->Gradient->Color1 = (TAlphaColor)0xFFDEE7F2; // Very light pastel
    this->Fill->Gradient->Style = TGradientStyle::Linear;

    // Style Title Label
    Label1->Text = "Task Scheduler";
    Label1->Font->Family = "Segoe UI";       // Modern sans-serif font
    Label1->Font->Size = 30;                 // Larger size for prominence
    Label1->Font->Style = TFontStyles() << fsBold;
    Label1->TextSettings->HorzAlign = TTextAlign::Center;
    Label1->TextSettings->VertAlign = TTextAlign::Center;
    Label1->TextSettings->FontColor = TAlphaColorRec::White;  // White text for contrast

    // Center the label on the left side
    Label1->Position->X = (this->Width / 4) - (Label1->Width / 2);  // Center on the left panel
    Label1->Position->Y = 20;                                      // Position near the top
}

//---------------------------------------------------------------------------
// Initialize TasksListBox
void TForm1::InitializeTasksListBox()
{
    if (TasksListBox == nullptr) {
        TasksListBox = new TListBox(this);
        TasksListBox->Parent = this;
        TasksListBox->Align = TAlignLayout::Client;
        TasksListBox->OnItemClick = TasksListBoxItemClick; // Attach event handler
    }
}

//---------------------------------------------------------------------------
// Add Task Event
void __fastcall TForm1::ADDClick(TObject *Sender)
{
    String taskText = TaskEdit->Text.Trim();

    if (taskText.IsEmpty()) {
        ShowMessage("Please enter a valid task.");
        return;
    }

    // Add task to the list
    TListBoxItem *newItem = new TListBoxItem(TasksListBox);
    newItem->Parent = TasksListBox;
    newItem->Text = taskText;

    // Style each list item
    newItem->StyledSettings = TStyledSettings() << TStyledSetting::FontColor; // Allow font color customization
    newItem->TextSettings->FontColor = TAlphaColorRec::Blue;                  // Blue text
    newItem->TextSettings->Font->Size = 14;                                  // Slightly smaller font

    TaskEdit->Text = "";
}

//---------------------------------------------------------------------------
// Highlight Task on Item Click
void __fastcall TForm1::TasksListBoxItemClick(TCustomListBox * const Sender, TListBoxItem * const Item)
{
    if (TasksListBox == nullptr) {
        ShowMessage("TasksListBox is not initialized.");
        return;
    }

    if (Item == nullptr) {
        ShowMessage("No task selected.");
        return;
    }

    // Unhighlight the previously selected task
    if (SelectedTask != nullptr) {
        SelectedTask->StyledSettings = TStyledSettings() << TStyledSetting::FontColor; // Reset styles
        SelectedTask->TextSettings->FontColor = TAlphaColorRec::Blue;                  // Reset text color
    }

    // Highlight the clicked task
    SelectedTask = Item;
    SelectedTask->StyledSettings = TStyledSettings() << TStyledSetting::FontColor; // Allow font color changes
    SelectedTask->TextSettings->FontColor = TAlphaColorRec::White;                // Change text to white
}

//---------------------------------------------------------------------------
// Delete Task on Delete Button Click
void __fastcall TForm1::DeleteBtnClick(TObject *Sender)
{
    if (SelectedTask == nullptr) {
        ShowMessage("No task selected for deletion.");
        return;
    }

    try {
        int index = SelectedTask->Index;
        if (index < 0 || index >= TasksListBox->Items->Count) {
            ShowMessage("Invalid index: " + IntToStr(index));
            return;
        }

        // Delete the selected task
        TasksListBox->Items->Delete(index);

        // Clear the SelectedTask pointer
        SelectedTask = nullptr;
    }
    catch (const Exception &e) {
        ShowMessage("Error: " + e.Message);
    }
}

//---------------------------------------------------------------------------
// Set Reminder Event
void __fastcall TForm1::SetReminderBtnClick(TObject *Sender)
{
    TDate reminderDate = ReminderDate->Date;
    TTime reminderTime = ReminderTime->Time;

    TDateTime reminderDateTime = reminderDate + reminderTime;
    TDateTime remainingTime = reminderDateTime - Now();

    double remainingTimeInMilliseconds =
        static_cast<double>(remainingTime) * MillisecondsPerDay;

    if (remainingTimeInMilliseconds <= 0) {
        ShowMessage("Please select a future date and time for the reminder.");
        return;
    }

    ReminderTimer->Interval = remainingTimeInMilliseconds;
    ReminderTimer->Enabled = true;

    ShowMessage("Reminder set successfully!");
}

//---------------------------------------------------------------------------
// Trigger Reminder
void __fastcall TForm1::ReminderTimerTimer(TObject *Sender)
{
    ReminderTimer->Enabled = false;

    ShowMessage(ReminderMessage->Text);
}

