use std::io;

fn main() {
    println!("Guess the number!");
    println!("Please input yur guess.");

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");

    // Print text to the console
    println!("You guessed: {}", guess);
}
