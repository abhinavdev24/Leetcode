#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution;

impl Solution {
    pub fn sort_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        fn get_len(head: &Option<Box<ListNode>>) -> usize {
            let mut len = 0;
            let mut current = head.as_ref();
            while let Some(node) = current {
                len += 1;
                current = node.next.as_ref();
            }
            len
        }

        fn merge(a: Option<Box<ListNode>>, b: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
            let mut dummy = Some(Box::new(ListNode::new(0)));
            let mut tail = &mut dummy;
            let mut a = a;
            let mut b = b;
            while a.is_some() && b.is_some() {
                let a_val = a.as_ref().unwrap().val;
                let b_val = b.as_ref().unwrap().val;
                if a_val < b_val {
                    let next = a.as_mut().unwrap().next.take();
                    tail.as_mut().unwrap().next = a;
                    a = next;
                } else {
                    let next = b.as_mut().unwrap().next.take();
                    tail.as_mut().unwrap().next = b;
                    b = next;
                }
                tail = &mut tail.as_mut().unwrap().next;
            }
            if a.is_some() {
                tail.as_mut().unwrap().next = a;
            }
            if b.is_some() {
                tail.as_mut().unwrap().next = b;
            }
            dummy.unwrap().next
        }

        let len = get_len(&head);
        if len <= 1 {
            return head;
        }

        let mid = len / 2;
        let mut head = head;
        let mut current = &mut head;
        for _ in 0..mid {
            current = &mut current.as_mut().unwrap().next;
        }

        let right = current.take();
        let left = head;
        let left_sorted = Self::sort_list(left);
        let right_sorted = Self::sort_list(right);
        merge(left_sorted, right_sorted)
    }
}

fn build_list(values: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &v in values.iter().rev() {
        let mut node = Box::new(ListNode::new(v));
        node.next = head;
        head = Some(node);
    }
    head
}

fn list_to_vec(mut head: Option<Box<ListNode>>) -> Vec<i32> {
    let mut out = Vec::new();
    while let Some(node) = head {
        out.push(node.val);
        head = node.next;
    }
    out
}

fn main() {
    let samples = vec![
        (vec![4, 2, 1, 3], vec![1, 2, 3, 4]),
        (vec![-1, 5, 3, 4, 0], vec![-1, 0, 3, 4, 5]),
        (vec![], vec![]),
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let head = build_list(&input);
        let result_head = Solution::sort_list(head);
        let result = list_to_vec(result_head);

        println!("Sample {}: head = {:?}", idx + 1, input);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\\n", expected);
    }
}
