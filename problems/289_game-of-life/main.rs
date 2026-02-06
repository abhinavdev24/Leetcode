struct Solution;

impl Solution {
    pub fn game_of_life(board: &mut Vec<Vec<i32>>) {
        if board.is_empty() || board[0].is_empty() {
            return;
        }
        let m = board.len();
        let n = board[0].len();
        let dr = [-1, -1, -1, 0, 0, 1, 1, 1];
        let dc = [-1, 0, 1, -1, 1, -1, 0, 1];

        // 1st pass: mark transitions
        for r in 0..m {
            for c in 0..n {
                let mut live = 0;
                for k in 0..8 {
                    let nr = r as i32 + dr[k];
                    let nc = c as i32 + dc[k];
                    if nr >= 0 && nr < m as i32 && nc >= 0 && nc < n as i32 {
                        let v = board[nr as usize][nc as usize];
                        if v == 1 || v == 2 {
                            live += 1;
                        }
                    }
                }
                if board[r][c] == 1 {
                    if live < 2 || live > 3 {
                        board[r][c] = 2; // live -> dead
                    }
                } else {
                    if live == 3 {
                        board[r][c] = 3; // dead -> live
                    }
                }
            }
        }

        // 2nd pass: finalize
        for r in 0..m {
            for c in 0..n {
                board[r][c] &= 1;
            }
        }
    }
}

fn main() {
    let samples = vec![
        (
            vec![vec![0, 1, 0], vec![0, 0, 1], vec![1, 1, 1], vec![0, 0, 0]],
            vec![vec![0, 0, 0], vec![1, 0, 1], vec![0, 1, 1], vec![0, 1, 0]],
        ),
        (vec![vec![1, 1], vec![1, 0]], vec![vec![1, 1], vec![1, 1]]),
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let mut board = input.clone();
        Solution::game_of_life(&mut board);

        println!("Sample {}: board = {:?}", idx + 1, input);
        println!("Placeholder result: {:?}", board);
        println!("Expected output: {:?}\\n", expected);
    }
}
