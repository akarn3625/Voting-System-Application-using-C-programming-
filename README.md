# 🗳️ Voting System in C

This project is a **console-based Voting System** built in C, designed to simulate a simple election process. It allows **admins** to manage elections and **voters** to register, log in, and cast their votes. The system ensures persistence by saving and loading data from files.

---

## 📌 Features

### 👨‍💼 Admin
- Secure login with default credentials (`admin/admin`)
- Create election schedule (stored in `schedule.txt`)
- Register candidates with name, party, and constituency
- Update voter details
- Search voter information
- View all voter details (including voting status and chosen candidate)
- Display election results

### 🧑 Voter
- Register as a voter (with eligibility check: must be 18+)
- Login using **Voter SNO** and password
- Cast a vote for available candidates
- Prevents double voting

### 💾 Data Handling
- Save and load candidate and voter details from `votingdetails.txt`
- Election schedule stored in `schedule.txt`

