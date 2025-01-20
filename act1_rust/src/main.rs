use std::env;
use std::fs;


struct Config {
    query: String,
    filepath: String,
}

fn parse_config(args: &[String]) -> Config {
    let query = args[1].clone();
    let filepath =args[2].clone();
    
    Config { query, filepath }
}


fn is_valid_print_statement(line : &str) -> bool {
    match line.trim().starts_with("print") && line.trim().ends_with(";") {
        true => return true,
        false => return false,
    };

    let open = line.chars()
        .filter(|&c| c == '(')
        .count();

    let close = line.chars()
        .filter(|&c| c == ')')
        .count();

    if open != 1 || close != 1 {
        return false;
    }   
    let quote = line.chars()
        .filter(|&c| c == '"')
        .count();
    
    if quote != 2 {
        return false;
    }

    true


} 

fn main() {
    
    let args : Vec<String> = env::args().collect();
    let config = parse_config(&args);

    let contents = fs::read_to_string(config.filepath)
        .expect("Not able to read the file");

    assert_eq!(is_valid_print_statement(&contents), true);

}
