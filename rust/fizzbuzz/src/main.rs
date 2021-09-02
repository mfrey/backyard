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

#[test]
fn fizzbuzz_test() {
    let mut result = fizzbuzz(3);
    assert!(result == "Fizz");
    result = fizzbuzz(5);
    assert!(result == "Buzz");
    result = fizzbuzz(15);
    assert!(result == "FizzBuzz");
    result = fizzbuzz(4);
    assert!(result == "4");
}

fn main() {
    for i in 1..=100 {
        let s = fizzbuzz(i);
        println!("{}", s);
    }
}
