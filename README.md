
# Project Overview

This project is structured to facilitate the development and testing of C/C++ based applications within a Dockerized environment, using Visual Studio Code as the primary IDE. The project architecture is organized to enhance productivity and streamline the development workflow.

## Project Structure

```plaintext
.
├── app
│   ├── build           # Compiled binaries and object files
│   ├── Inc             # Header files
│   ├── Makefile        # Build automation
│   └── Src             # Source files
├── .devcontainer
│   └── devcontainer.json  # Configuration for VSCode Development Containers
├── Dockerfile          # Docker configuration for consistent dev environments
├── .git                # Git repository folders and files
├── README.md           # Project documentation
└── .vscode
    ├── launch.json     # Debug configurations
    ├── settings.json   # Editor settings
    └── tasks.json      # Task configurations for build and utility commands
```

## Features

### Automated Builds
- The `Makefile` in the `app` directory automates the build process. It compiles the source files from the `Src` directory, using headers in the `Inc` directory, and outputs the binaries and object files to the `build` directory.

### Debugging
- The project supports debugging through the configuration set in `.vscode/launch.json`. This setup integrates with the Docker environment, allowing for seamless debugging sessions that mimic production environments closely.

### Docker Integration
- A `Dockerfile` and `.devcontainer/devcontainer.json` are included to ensure that the development environment is reproducible and consistent across different setups, minimizing "works on my machine" issues.

### VSCode Integration
- The `.vscode` folder contains custom settings, tasks, and debug configurations to optimize the development experience. Tasks for building, cleaning, and running the application are predefined for ease of use.

## Getting Started

To get started with this project, clone the repository and ensure you have Docker and Visual Studio Code installed with the Remote - Containers extension enabled. Open the project in VSCode, and it will prompt you to reopen it in a container. This ensures all dependencies and toolchains are correctly set up for anyone working on the project.

## Running the Application

To build and run the application:
1. Open the command palette (`Ctrl+Shift+P`) and execute the `Build` task to compile the application.
2. Run the application by executing the `Run` task from the command palette.

## Debugging

To debug the application:
1. Set breakpoints in the source code as necessary.
2. Start a debugging session by selecting the `(gdb) Launch App` configuration from the debug panel and hitting `F5`.

This setup not only enhances your development efficiency but also keeps your workspace organized by providing quick access to frequently used commands directly from the IDE.
