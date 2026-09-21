# CPP Brainfuck Interpreter
Pretty simple "interpreter", a reintroduction to cpp.


*Below evaluation using AI because I am lazy*
## Status

Working interpreter: full language, 8-bit wrapping cells, 30 000-cell tape,
EOF reads as 0. Pipeline is `lex` → `parse` (merges runs of `+-<>`, links
`[`/`]` jump targets) → `interpret` (switch dispatch over the IR).
Measured ~1.8 ns/instruction at `-O3`.

## TODO

Roughly in the order worth doing them.

### 1. Work

- [ ] Bounds-check `Move` in the interpreter. `<.` currently reads memory
      before the tape without any error.
- [ ] Add `-Wall -Wextra -Wconversion` to the target (would have caught the
      signed/unsigned `ptr += inst.arg`).
- [ ] Add tests (CTest): hello world, `-.` wraparound, `,[.,]` cat, unmatched
      `[` and `]`, tape underflow. Do this before touching the optimizer.
- [ ] Include `<algorithm>` for `std::max` in `interpreter.cpp`.
- [ ] Decide on and document the EOF convention (0 / 255 / unchanged).

### 2. Fast

Dispatch is not the bottleneck; the parser only doing run-length merging is.
Superinstructions, by payoff:

- [ ] `[-]` / `[+]` → `Clear`
- [ ] `[->+<]`, `[->++>+<<]`, … → `MulAdd` (loop body with net move 0, one
      `Add -1` at offset 0, only `Add`s elsewhere)
- [ ] Fold `Move` into the following op as an offset operand, so `>>+++<<`
      becomes `Add{+3, offset 2}` without moving the pointer
- [ ] `[>]` / `[<]` → `Scan`
- [ ] Drop net-zero results of merging (`+-` currently leaves an `Add 0`)
- [ ] Use `std::putchar` instead of `std::print("{}", char)` for `Output`

Expect 3–10× from the above. Computed-goto dispatch / JIT only after that.

### 3. Error handling and user feedback

- [ ] Report errors as `file:line:col` instead of a byte offset. Keep
      `offset` in the IR; translate it in `main.cpp` where the source is.
- [ ] Introduce `bf::Error` (carries the offset) so runtime errors get the
      same treatment as parse errors.

### Nice to have

- [ ] `Op op{}` in `ir.hpp`: either `Op op = Op::Add;` or drop the default
      and rely on designated initializers.
- [ ] Rename `parse` → `optimize` once it grows superinstructions; it is
      already more optimizer + linker than parser.
