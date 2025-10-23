# 🧭 Project Overview

**Event Management App** is a desktop application built in **C++** using the **Qt framework**, designed for efficient event management.  
It allows **users** and **administrators** to create, update, delete, and view events, export lists (CSV/HTML), and provides **undo/redo functionality**.

---

## 🧠 The Project Demonstrates

- Clean **object-oriented programming** principles (inheritance, polymorphism)  
- A **layered architecture** separating domain, service, and GUI layers  
- Practical **GUI programming** using Qt Widgets  
- Advanced user interactions like **Undo/Redo** via the Command Pattern  

---

## 💡 What It Solves

- Organizes and tracks events with attributes such as **date/time**, **description**, and **type**  
- Provides **role-based operations** for admins and users  
- Implements an **undo/redo stack** to maintain action history and recover from mistakes  
- Supports **data export** for reporting or sharing in **CSV** and **HTML** formats  

---

## 🎮 Usage

### 👩‍💼 Admin Mode
- Add, edit, or delete events  
- Undo/Redo changes  
- Export event list to CSV or HTML  

### 👤 User Mode
- Browse and view events  
- Save favorite events *(if implemented)*  

### ⌨️ Keyboard Shortcuts
- `Ctrl + Z` → Undo  
- `Ctrl + Y` → Redo  

---

## ⚙️ Technology Stack

| Component | Description |
|------------|--------------|
| **Language** | C++ (pure, no managed code) |
| **GUI Framework** | Qt (Qt Widgets) |
| **Data Storage** | In-memory + file-based persistence (CSV/HTML export) |
| **Design Patterns** | Command Pattern (for undo/redo), Model-View (Qt’s QAbstractTableModel) |
| **Platform** | Desktop application (Windows/Linux) |

---
