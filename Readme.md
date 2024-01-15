# AST-Playground

Welcome to AST-Playground, a light-hearted and educational open-source project born out of curiosity and a love for coding experiments. This repository is the playground where I delve into the intricacies of Abstract Syntax Trees (AST), particularly focusing on double expressions. It's a place for fun, learning, and experimentation, all sparked by a random question I stumbled upon online.

## Project Insight

Here, you'll find a template for constructing an AST for double expressions, as described in the `problem.pdf` file. It's important to note that this project is very much a toy project—it's not intended for serious use, but rather as a personal experimental space for understanding ASTs better. Initial files can be found at `initial` branch.

### Repository Composition

- The requirements provided by the original exercise is located in the repository, which can be accessed through the link [problem.pdf](problem.pdf).
- The exercise's template suggests a monolithic file structure, hence the initial files may be more extensive than typical (some reaching around 300 lines). This structure was recommended for the exercise, and I've kept it in this initial phase for simplicity.
- The template assumes that inputs are valid, so error handling has not been incorporated into the initial version.

## Usage

To get a feel for the AST-Playground, simply clone the repository and take a look at the provided `problem.pdf` for a comprehensive understanding of what the project aims to tackle:

```bash
git clone https://github.com/AliAshkaniNia/AST-Playground.git
cd AST-Playground
mkdir build 
cmake -DCMAKE_BUILD_TYPE=Debug ../exercise1
make -j$(nproc)
./test/tester
```

Remember, this is a sandbox, so the emphasis is on creativity and experimentation, not on flawless code.



