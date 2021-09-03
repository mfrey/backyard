use std::fs::File;
use std::path::Path;

fn main() {
    let path = Path::new("src/data/hello.txt");
    //let display = path.display();

    let mut file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", path.display(), why),
        Ok(file) => file,
    };
}
