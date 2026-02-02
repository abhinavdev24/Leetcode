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
    pub fn insertion_sort_list(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if head.is_none() || head.as_ref().unwrap().next.is_none() {
            return head;
        }
        let mut dummy = Box::new(ListNode::new(0));
        let mut curr = head;
        while let Some(mut node) = curr {
            curr = node.next.take();
            let mut prev = &mut dummy;
            while prev.next.is_some() && prev.next.as_ref().unwrap().val < node.val {
                prev = prev.next.as_mut().unwrap();
            }
            node.next = prev.next.take();
            prev.next = Some(node);
        }
        dummy.next
    }
}

fn build_list(values: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &value in values.iter().rev() {
        let mut node = Box::new(ListNode::new(value));
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
    ];

    for (idx, (input, expected)) in samples.into_iter().enumerate() {
        let head = build_list(&input);
        let result_head = Solution::insertion_sort_list(head);
        let result = list_to_vec(result_head);

        println!("Sample {}: head = {:?}", idx + 1, input);
        println!("Placeholder result: {:?}", result);
        println!("Expected output: {:?}\n", expected);
    }
}
