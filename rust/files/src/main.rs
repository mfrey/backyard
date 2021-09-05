use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::io::BufReader;

fn main() {
    let path = Path::new("src/data/hello.txt");

    let file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", path.display(), why),
        Ok(file) => file,
    };

    let reader = BufReader::new(file).lines();
    let mut lines = 0;

    for i in reader {
       lines += 1;
       match i {
           Err(why) => panic!("could not read line {}, cause: {}", lines, why),
           Ok(line) => {
               if !line.is_empty() {
                   println!("{}", line)
               }
           }
       }
    }

    println!("total number of lines: {}", lines);
}
