# ⛸️ Speed Skating Competition Manager (C)

This repository contains a project developed in **C** to manage and score the Team Pursuit event in speed skating competitions. The application is designed to process various administrative and result-based commands to accurately track teams, record race times, and determine final rankings.

The project emphasizes core principles of **structured programming**, **memory management**, and **robust data handling** within the constraints of the C language.

## ✨ Key Features

- **Command Interpreter:** A robust `main` loop that accepts and executes a defined set of commands (e.g., `inscrire_equipe`, `definir_parcours`).
- **Data Structure Management:** Efficient use of C `struct` and arrays to model core entities:
    - **Patineur (Skater):** Name, bib number, and individual lap/race times.
    - **Equipe (Team):** Country, a fixed number of skaters (3), and maximum team time.
- **Competition Setup:** Commands to configure the event size:
    - `definir_parcours`: Set the number of courses/rounds in the competition (max 10).
    - `definir_nombre_epreuve`: Set the number of events (max 32).
- **Team Registration:** Handles the enrollment of teams, assigning unique team and skater IDs.
- **Race Results:** Logic to record and analyze race times, with the ability to disqualify or update teams based on performance.

---

## 🧱 Data Model & Architecture

The application is built on fundamental C data types and structures, designed for efficient memory use and direct access.

### Core Data Structures

| C Structure (`typedef struct`) | Role | Constants Used |
| --- | --- | --- |
| `Patineur` (Skater) | Stores individual athlete details, including their bib (`dossard`) and an array of times for multiple parcours/rounds. | `LGMOT` (Name Length), `NB_PARCOURSMAX` |
| `Equipe` (Team) | An array of structures representing all teams. Each team holds the data for its **3** skaters and its country name. | `NB_PATINEUR`, `NB_EQUIPE` |

### Command Flow

The `main` function acts as the central command dispatcher, continuously reading strings from standard input (`scanf("%s", mot);`) and executing the corresponding command function using `strcmp`.

---

## 🚀 Getting Started

This project is a standard C application requiring a basic C compiler.

### Prerequisites

- A C compiler (e.g., GCC or Clang).
- A Unix-like environment (Linux/macOS) or a C IDE.

### Compilation

1. **Clone the repository:**
    
    ```bash
    git clone [<https://github.com/jsacko/c-speed-skating-manager.git>](<https://github.com/jsacko/c-speed-skating-manager.git>)
    cd speed-skating
    
    ```
    
2. **Compile the source file using GCC:**
    
    ```bash
    gcc -Wall Sprint5_SackoJulien.c -o speed_skating
    
    ```
    
### Usage

Run the compiled executable and enter commands interactively:

```bash
./speed_skating
```

## 👨‍💻 Author

**Julien SACKO** | Machine Learning Engineer 

[LinkedIn](https://www.linkedin.com/in/julien-sacko/)
