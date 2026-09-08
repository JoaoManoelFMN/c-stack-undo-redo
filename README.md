# 📝 Task Manager — Stacks & Graphs in C

A command-line task manager developed as an academic project to practice **data structures, algorithms, pointers, and dynamic memory management in C**.

The application combines two main concepts:

* **Stack:** manages task creation and Undo/Redo operations using the LIFO principle.
* **Dependency Graph:** represents relationships between tasks and supports traversal using BFS and DFS.

## 🎯 Project Goals

The project was developed to practice:

* Stack implementation and manipulation
* Graph representation using adjacency lists
* Breadth-First Search (BFS)
* Depth-First Search (DFS)
* Dynamic memory allocation with `malloc` / `free`
* Pointer manipulation in C
* Modular code organization

## 🚀 Features

### Task Management

* Add tasks to the stack
* Complete and undo the most recent task
* Redo previously undone tasks
* View the top task
* Display all tasks
* Persist the current state before exiting
* Release dynamically allocated memory safely

### Dependency Graph

* Create relationships between tasks
* Find connected tasks using DFS
* Check connectivity between tasks using BFS
* Display the shortest path between two connected tasks

## 🏗️ Project Structure

```text
c-stack-undo-redo/
├── main.c
├── pilha.h
├── pilha.c
├── grafo.h
├── grafo.c
├── utils.h
├── utils.c
└── README.md
```

### Main Components

| File                  | Responsibility                           |
| --------------------- | ---------------------------------------- |
| `pilha.c` / `pilha.h` | Stack implementation and task management |
| `grafo.c` / `grafo.h` | Graph representation, BFS and DFS        |
| `utils.c` / `utils.h` | Utility functions and input handling     |
| `main.c`              | Application flow and user interaction    |

## 🧠 Data Structures & Algorithms

### Stack

Tasks are managed using a stack-based structure. Undo and Redo operations move task states between stacks.

### Dependency Graph

Task relationships are represented using an adjacency-list graph.

* **DFS** is used to find the connected component of a task.
* **BFS** is used to determine whether two tasks are connected and to retrieve the shortest path.

## 🛠️ Technologies

* C
* Data Structures
* Graph Algorithms
* Dynamic Memory Management
* GCC

## 🚀 Getting Started

### Requirements

* GCC or another C compiler
* Git

### Clone

```bash
git clone https://github.com/JoaoManoelFMN/c-stack-undo-redo.git
cd c-stack-undo-redo
```

### Compile

```bash
gcc -o task_manager main.c grafo.c pilha.c utils.c -Wall
```

### Run

```bash
./task_manager
```

## 🎓 Academic Context

Developed as a university project to apply concepts of **data structures, graph algorithms, memory management, and modular programming in C**.

## 👥 Contributors

* João Manoel Nunes
* João Pedro Magalhães
* Rafael Maia
* Leonardo Freitas Barboza
* Bruno Braga Ramos
