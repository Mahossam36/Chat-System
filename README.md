# 📬 Simple Chat Box System in C++

This is a console-based chat box system implemented in C++. It simulates a basic messaging platform with the following core functionalities:

## 📌 Features

- ✅ **User Signup/Login System**
- 💬 **Send Questions to Specific Users**
- 📥 **View Messages Sent to You**
- 📤 **View Messages Sent by You**
- ↩️ **Reply to Specific Questions**
- 🗑️ **Delete the Entire Chat**
- 📜 **View Full Chat History**
- 🟢 **See Active Users**
- 🚪 **Logout Functionality**

All data is saved and managed through text files.

---

## 📁 Project Structure

The project uses the following files for data storage:

| File Path | Purpose |
|----------|---------|
| `all user.txt` | Stores registered usernames and passwords |
| `active user.txt` | Tracks currently logged-in users |
| `Chat Box.txt` | Stores chat messages |
| `Messages ID.txt` | Stores used message IDs to ensure uniqueness |

> ⚠️ **Important:** The file paths are hardcoded to:  
> `C:/Users/hp/OneDrive/Desktop/Project/`.  
> Make sure to update them if needed or match this folder structure on your system.

---

## 🚀 How to Run

1. Open your C++ IDE (e.g., Visual Studio).
2. Make sure the project files and folders exist at:
3. Compile and run the `main()` function.
4. Start interacting with the program using the numeric menu.

---

## 🧠 How It Works

### Authentication
- Users can **sign up** with a username and password.
- On **login**, the program checks credentials against `all user.txt`.

### Messaging
- Users can **send questions** to others.
- Each message has a unique ID stored in `Messages ID.txt`.
- Replies are added under the original question.
- You can send messages **anonymously**.

### Menu Options

---

## 💡 Notes

- The system uses `\033` ANSI escape codes to add color to the terminal (may not work on all Windows environments).
- `filesystem::file_size()` is used to check if files are empty.

---

## 📸 Sample Output

```text
Menu:
        1: Print Question To Me
        2: Print Question From Me
        3: Reply On Question
        4: Delete Chat
        5: Add Question
        6: Active Users
        7: Open The Chat
        8: Logout
