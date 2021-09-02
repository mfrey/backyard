fn fizzbuzz(i: u32) -> String {
    let mut result = String::from("");

    match (i % 3, i % 5) {
        (0, 0) => result.push_str("FizzBuzz"),
        (0, _) => result.push_str("Fizz"),
        (_, 0) => result.push_str("Buzz"),
        (_, _) => result = format!("{}", i)
    }

    return result;
}

fn main() {
    for i in 1..=100 {
        let s = fizzbuzz(i);
        println!("{}", s);
    }
}
