#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.DateTimeCtrls.hpp>
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:    // IDE-managed Components
    TLabel *Label1;
    TEdit *TaskEdit;
    TButton *ADD;
    TDateEdit *ReminderDate;
    TTimeEdit *ReminderTime;
    TEdit *ReminderMessage;
    TButton *SetReminderBtn;
    TTimer *ReminderTimer;
    TListBox *TasksListBox;

    void __fastcall ADDClick(TObject *Sender);
    void __fastcall TasksListBoxItemClick(TCustomListBox * const Sender, TListBoxItem * const Item);
    void __fastcall DeleteBtnClick(TObject *Sender);
    void __fastcall SetReminderBtnClick(TObject *Sender);
    void __fastcall ReminderTimerTimer(TObject *Sender);

private:    // User declarations
    TButton *DeleteBtn;
    TListBoxItem *SelectedTask;

    void InitializeTasksListBox();
    void ApplyModernStyling();

public:     // User declarations
    __fastcall TForm1(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

