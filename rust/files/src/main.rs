use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

fn main() {
    let path = Path::new("src/data/hello.txt");

    let mut file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", path.display(), why),
        Ok(file) => file,
    };

    let mut buffer = String::new();
    match file.read_to_string(&mut buffer) {
        Err(why) => panic!("coult not read file {}", why),
        Ok(bytes_read) => println!("read {} bytes", bytes_read)
    }
    println!("{}", buffer);
}
