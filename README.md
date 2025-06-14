# Task Reminder App (C++ Builder + FireMonkey)

A simple desktop task scheduler and reminder app built using **Embarcadero C++ Builder** and the **FireMonkey (FMX) UI framework**. The app allows users to create tasks, set timed reminders, and receive visual alerts — all with a clean, modern interface.

---

## 🚀 Features

- ✅ Add tasks to a scrollable task list
- ⏰ Set custom reminders using date & time pickers
- 🧾 Automatic popup notifications when reminders are triggered
- 🧹 Delete tasks with a dedicated DELETE button
- 🎨 Custom styling using gradient backgrounds and modern fonts

---

## 🛠 Built With

- **Embarcadero C++ Builder (FMX)**
- **FireMonkey Framework** (cross-platform GUI)
- **Object Pascal Runtime + C++ syntax**

---

## 🖼 UI Highlights

- Modern pastel blue gradient background
- Centralized title label using Segoe UI
- Dynamic styling of task items (blue and white text highlighting)
- Fully responsive layout with list box integration

---

## 🧠 Core Logic

- `ReminderTimer`: waits until the user-set time, then displays the reminder message
- `TListBox`: used to dynamically list, highlight, and delete tasks
- Pointer handling for `SelectedTask` ensures correct item selection and deletion

---



## 📁 File Structure

├── Unit1.cpp # Main app logic
├── Unit1.h # Header file
├── *.fmx # FireMonkey UI layout

---

## 📌 Author

Ayesha Riaz  
Business Analytics Student @ FAST NUCES  
---

## ⚠️ Note

- Make sure you have **C++ Builder installed with FMX support**.
- This app is designed primarily for **Windows desktop** environments.

---

