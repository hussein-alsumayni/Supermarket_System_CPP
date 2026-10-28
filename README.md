# Super Market Management System (C++ Console Application)

## 📌 Project Overview
This repository contains a robust, console-based **Super Market Management System** implemented in **C++**. Designed with a modular architecture and persistent file storage, the system manages user authentication, role-based access control (RBAC), inventory tracking, sales transactions, and automated reporting.

---

## 🛠️ Features & Implementation Details

1. **Role-Based Authentication & User Management (Admin):**
   * Secure login system with active/inactive account status enforcement.
   * **Admin Privileges:** Add new users (with strict validation for alphabetic usernames and valid Yemeni mobile prefixes: `77`, `73`, `71`, `78`), view user directories, manage account statuses (activate/deactivate), delete users (with root admin protection), and view system statistics.

2. **Inventory & Product Management (Employee):**
   * Full CRUD operations for products (Add, View, Search, Update, and Delete).
   * Robust input validation ensuring numeric pricing and positive quantities.

3. **Sales & Automated Invoicing:**
   * Direct point-of-sale processing that automatically updates inventory levels upon successful checkout.
   * Generates real-time transaction invoices and logs sales data persistently.

4. **Reporting & Analytics:**
   * Aggregates total sales revenue and compiles ranked performance metrics to display the **Top 5 Best-Selling Products**.

---

## 🚀 Quick Start / How to Run

1. **Compilation Requirements:**
   * A standard C++ compiler supporting C++11 or later (e.g., `g++`, `MinGW`, or MSVC).
2. **Execution:**
   * Compile and run `porject.cpp` in your preferred IDE (Code::Blocks, Dev-C++, VS Code).
3. **Default Admin Credentials:**
   * **Username:** `admin`
   * **Password:** `1234`
