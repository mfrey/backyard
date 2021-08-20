extern crate rand;

use std::io;
use rand::{thread_rng, Rng};

fn main() {
    println!("Guess the number!");

    let secret_number = thread_rng().gen_range(1..101);
    println!("The secret number is: {}", secret_number);

    println!("Please input yur guess.");

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    println!("You guessed: {}", guess);
}
