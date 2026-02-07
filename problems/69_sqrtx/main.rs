struct Solution;

impl Solution {
    pub fn my_sqrt(x: i32) -> i32 {
        if x < 2 {
            return x;
        }
        let mut l = 1;
        let mut r = x / 2;
        let mut ans = 0;
        while l <= r {
            let mid = l + (r - l) / 2;
            if mid <= x / mid {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans
    }
}

fn main() {
    let samples = vec![(4, 2), (8, 2)];

    for (x, expected) in samples {
        let result = Solution::my_sqrt(x);
        println!(
            "input: x = {}, placeholder result: {}, expected: {}",
            x, result, expected
        );
    }
}
