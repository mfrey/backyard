extern crate url;

use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::io::BufReader;
use url::Url;


fn parse_url(line: String) -> Option<Url> {
    match Url::parse(&line) {
        Ok(url) => Some(url),
        Err(_) => None
    }
}

#[test]
fn parse_url_valid() {
    assert!(parse_url(String::from("https://github.com")).is_some());
}

#[test]
fn parse_url_invalid() {
    assert!(parse_url(String::from("some string")).is_none());
}

fn main() {
    let path = Path::new("src/data/hello.txt");

    let file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", path.display(), why),
        Ok(file) => file,
    };

    let reader = BufReader::new(file).lines();

    for i in reader {
       let line = match i {
           Err(why) => panic!("could not read line: {}", why),
           Ok(content) => content 
       };

       let url = parse_url(line);
       match url {
           None => continue,
           Some(line) => println!("{}", line)
       }
    }
}
