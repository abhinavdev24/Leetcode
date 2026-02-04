struct Solution;

impl Solution {
    pub fn roman_to_int(s: String) -> i32 {
        let chars: Vec<char> = s.chars().collect();
        let mut ans = 0;
        let mut i = 0;
        while i < chars.len() {
            match chars[i] {
                'I' => {
                    if i + 1 < chars.len() && chars[i + 1] == 'V' {
                        ans += 4;
                        i += 2;
                    } else if i + 1 < chars.len() && chars[i + 1] == 'X' {
                        ans += 9;
                        i += 2;
                    } else {
                        ans += 1;
                        i += 1;
                    }
                }
                'V' => {
                    ans += 5;
                    i += 1;
                }
                'X' => {
                    if i + 1 < chars.len() && chars[i + 1] == 'L' {
                        ans += 40;
                        i += 2;
                    } else if i + 1 < chars.len() && chars[i + 1] == 'C' {
                        ans += 90;
                        i += 2;
                    } else {
                        ans += 10;
                        i += 1;
                    }
                }
                'L' => {
                    ans += 50;
                    i += 1;
                }
                'C' => {
                    if i + 1 < chars.len() && chars[i + 1] == 'D' {
                        ans += 400;
                        i += 2;
                    } else if i + 1 < chars.len() && chars[i + 1] == 'M' {
                        ans += 900;
                        i += 2;
                    } else {
                        ans += 100;
                        i += 1;
                    }
                }
                'D' => {
                    ans += 500;
                    i += 1;
                }
                'M' => {
                    ans += 1000;
                    i += 1;
                }
                _ => {}
            }
        }
        ans
    }
}

fn main() {
    let sample1 = String::from("III");
    let sample2 = String::from("LVIII");
    let sample3 = String::from("MCMXCIV");

    let result1 = Solution::roman_to_int(sample1);
    println!("Sample 1 placeholder result: {}", result1);
    println!("Sample 1 expected output: 3\n");

    let result2 = Solution::roman_to_int(sample2);
    println!("Sample 2 placeholder result: {}", result2);
    println!("Sample 2 expected output: 58\n");

    let result3 = Solution::roman_to_int(sample3);
    println!("Sample 3 placeholder result: {}", result3);
    println!("Sample 3 expected output: 1994");
}
