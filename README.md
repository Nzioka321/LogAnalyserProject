# Log Analyser Project

## Overview
This project integrates a C++ Log Analyzer with an ASP.NET Core MVC Web Application.

The system allows users to upload a log file via the web interface.  
The web application executes a C++ executable to analyze the log and displays the results in the browser.

---

## Technologies Used
- C++
- ASP.NET Core (.NET 6+)
- MVC Architecture
- File Upload Handling
- Process Execution (C++ from Web App)
- Git & GitHub

---

## Features
- Log file upload
- INFO, WARNING, ERROR count
- Error burst detection (5+ errors within 10 seconds)
- Result display in browser

---

## How It Works
1. User uploads a log file.
2. ASP.NET saves the file temporarily.
3. Web app calls the C++ executable.
4. C++ analyzes the file.
5. Results are returned and displayed.

---

## Author
Your Name
