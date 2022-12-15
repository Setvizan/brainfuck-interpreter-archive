use std::fs;
use std::env;
use std::io::Read;
use std::ops::Index;

enum Inst {
    Right,
    Left,
    Increment,
    Decrement,
    Write,
    Read,
    LoopOpen,
    LoopClose
}

fn lex(source: String) -> Vec<Inst> {
    let mut instructions: Vec<Inst> = Vec::new();

    for char in source.chars() {
        match char {
            '>' => instructions.push(Inst::Right),
            '<' => instructions.push(Inst::Left),
            '+' => instructions.push(Inst::Increment),
            '-' => instructions.push(Inst::Decrement),
            '.' => instructions.push(Inst::Write),
            ',' => instructions.push(Inst::Read),
            '[' => instructions.push(Inst::LoopOpen),
            ']' => instructions.push(Inst::LoopClose),
            _ => ()
        };
    }

    return instructions
}

fn process_jumps(instructions: &Vec<Inst>) -> Vec<usize> {
    let mut jump_table: Vec<usize> = vec![0; 30000];
    let mut stack: Vec<usize> = Vec::new();
    for (i, inst) in instructions.iter().enumerate() {
        match inst {
            Inst::LoopOpen => stack.push(i),
            Inst::LoopClose => {
                let index: usize = stack.pop().unwrap();
                jump_table[i] = index;
                jump_table[index] = i;
            }
            _ => ()
        }
    }
    return jump_table;
}

fn run(instrument: &Vec<Inst>, pointer: &mut usize, tape: &mut Vec<u8>, jump_table: &Vec<usize>){
    let mut index: usize = 0;
    while index < instrument.len() {
        let inst = instrument.index(index);
        match inst {
            Inst::Right => *pointer += 1,
            Inst::Left => *pointer -= 1,
            Inst::Increment => tape[*pointer] += 1,
            Inst::Decrement => tape[*pointer] -= 1,
            Inst::Write => print!("{}", tape[*pointer] as char),
            Inst::Read => {
                let mut input: [u8; 1] = [0; 1];
                std::io::stdin().read_exact(&mut input).expect("failed to read stdin");
                tape[*pointer] = input[0];
            }
            Inst::LoopOpen => {
                if tape[*pointer] == 0 { index = jump_table[index]}
            }
            Inst::LoopClose => {
                if tape[*pointer] != 0 { index = jump_table[index]}
            }
        }
        index += 1;
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("usage: brainfuck <file>");
        std::process::exit(1);
    }

    let file_path = &args[1];

    let file_source = fs::read_to_string(file_path).expect("kill yourself");

    let instructions = lex(file_source);

    let jump_table = process_jumps(&instructions);

    let mut tape: Vec<u8> = vec![0;30000];

    let mut pointer: usize = 0;

    run(&instructions, &mut pointer, &mut tape, &jump_table)
}