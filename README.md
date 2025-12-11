# Data Structure and Algorithms

This is a whole new round of algorithm learning. I'm planning to implement all data structures with Go for two reasons:

1. Familiarize myself with the Go programming language.
2. Make myself comfortable with algorithms again after nearly a year.

I expect this round of learning and implementing to be easier and smoother than before, as I have done it several times before.
Also, I should be taking advantage of this round to practice my English writing skills as well.

## Project Structure

```
joseph/algo/
├── datastructure/          # Data structure implementations
│   ├── array/
│   │   ├── array.go
│   │   └── array_test.go
│   └── linkedlist/
│       ├── linkedlist.go
│       └── linkedlist_test.go
├── algorithm/              # Algorithm implementations
│   └── sorting/            # Sorting algorithms (to be added)
│       ├── bubble/
│       │   ├── bubble.go
│       │   └── bubble_test.go
│       └── quick/
│           ├── quick.go
│           └── quick_test.go
├── leetcode/              # LeetCode problems
│   └── e283_move_zeros/
│       └── README.md
└── examples/              # All example programs
    ├── array/
    │   └── main.go
    ├── linkedlist/
    │   └── main.go
    └── leetcode/
        └── main.go
```

## Design Principles

### 1. Categorization by Function
- **datastructure/**：All data structure implementations (arrays, linked lists, stacks, queues, etc.)
- **algorithm/**：All algorithm implementations (sorting, searching, dynamic programming, etc.)
- **leetcode/**：LeetCode problems and solutions
- **examples/**：All example programs managed in one place

### 2. Unified Example Management
- All `main.go` files are placed in subdirectories under `examples/`
- Each example program is in its own subdirectory to avoid `main` function conflicts
- Example programs are not executed by `go test ./...`

### 3. Test Isolation
- Each module has its own `*_test.go` file
- `go test ./datastructure/...` only tests data structures
- `go test ./algorithm/...` only tests algorithms
- The `examples/` directory does not contain tests and will not be executed during testing

## About main.go

### Why shouldn't main.go be in the package directory?

1. **Package Design Principles**:
   - Go packages should be reusable libraries and should not contain executable programs
   - If a package directory contains `main.go`, that package cannot be imported by other packages

2. **Testing Issues**:
   - `go test ./...` will attempt to compile all directories
   - Directories containing `main.go` will be treated as executable programs rather than tests
   - This will cause test failures or unexpected behavior

3. **Import Issues**:
   - If the `array/` directory contains `main.go`, other packages cannot import `joseph/algo/array`
   - Because Go will consider it an executable program, not a library

### Solution

- **Unified example programs in examples directory**: All demonstration code is centrally managed
- **Each example program in its own subdirectory**: Avoids `main` function conflicts
- **Exclude examples during testing**: Use `go test ./datastructure/...` instead of `go test ./...`

## Usage

### Running Example Programs
```bash
make run-array        # Run array example
make run-linkedlist  # Run linked list example
make run-leetcode     # Run LeetCode example
make run-all          # Run all examples
```

### Running Tests
```bash
make test             # Run all unit tests (excluding examples)
make test-array       # Test array only
make test-linkedlist  # Test linked list only
make test-coverage    # Generate coverage report
```

### Import and Use
```go
import (
    "joseph/algo/datastructure/array"
    "joseph/algo/datastructure/linkedlist"
)

func main() {
    arr := array.NewArray(10)
    ll := linkedlist.NewLinkedList()
    // ...
}
```

## Implementation Progress

### Data Structures

- [x] Array
- [x] Linked List
- [ ] Stack
- [ ] Queue
- [ ] Tree
- [ ] Hash Table
- [ ] Graph

### Sorting Algorithms

- [ ] Bubble Sort
- [ ] Selection Sort
- [ ] Insertion Sort
- [ ] Shell Sort
- [ ] Merge Sort
- [ ] Quick Sort
- [ ] Heap Sort
- [ ] Counting Sort
- [ ] Radix Sort
- [ ] Bucket Sort

### Strategies

- [ ] Recursion
- [ ] Dynamic Programming
- [ ] Greedy Algorithm
- [ ] Backtracking

### LeetCode Solutions

- [x] [283. Move Zeroes](./leetcode/e283_move_zeros/README.md)

## Future Extensions

### Adding New Data Structures
1. Create a new directory under `datastructure/` (e.g., `stack/`)
2. Implement `stack.go` and `stack_test.go`
3. Create `stack/` directory and `main.go` under `examples/`

### Adding New Algorithms
1. Create a new directory under `algorithm/sorting/` (e.g., `merge/`)
2. Implement `merge.go` and `merge_test.go`
3. Create corresponding example programs under `examples/` if needed

### Adding LeetCode Problems
1. Create a new directory under `leetcode/` (e.g., `e1_two_sum/`)
2. Implement `solution.go` and `solution_test.go`
3. Add corresponding examples under `examples/leetcode/` if needed

## Advantages

1. **Clear hierarchical structure**: Categorized by function, easy to find and maintain
2. **Test isolation**: Example programs do not interfere with tests
3. **Easy to extend**: Adding new content only requires creating in the corresponding directory
4. **Follows Go best practices**: Packages as libraries, example programs managed independently
