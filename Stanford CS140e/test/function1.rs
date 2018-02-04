fn add2(x: i32, y: i32) -> i32 {
	return x+y;
}

fn main() {
	let x: i32 = 1;
	let y: i32 = 13i32;
	let sum =  add2(x, y);
	let c: &str = "hello world";
	println!("{} {}", sum, c);
}