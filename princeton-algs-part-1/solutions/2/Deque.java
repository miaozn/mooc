import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item>
{
    
    
    private class ListNode
    {
        Item val;
        ListNode prev;
        ListNode next;
        
        public ListNode(Item v)
        {
            val = v;
            prev = null;
            next = null;
        }
    }
    
    
    private ListNode _dummyHead;
    private ListNode _dummyTail;
    private int _size;
    
    
    private void link(ListNode lo, ListNode hi)
    {
        lo.next = hi;
        hi.prev = lo;
    }
    
    public Deque()
    {
        _dummyHead = new ListNode(null);
        _dummyTail = new ListNode(null);
        link(_dummyHead, _dummyTail);
        _size = 0;
    }
    
    public boolean isEmpty()
    {
        return _size == 0;
    }
    
    
    public int size()
    {
        return _size;
    }
    
    public void addFirst(Item item)
    {
        if (item == null) throw new java.lang.NullPointerException();
        ListNode node = new ListNode(item);
        ListNode next = _dummyHead.next;
        link(_dummyHead, node);
        link(node, next);
        ++_size;
        
    }
    
    public void addLast(Item item)
    {
        if (item == null) throw new java.lang.NullPointerException();
        ListNode node = new ListNode(item);
        ListNode prev = _dummyTail.prev;
        link(prev, node);
        link(node, _dummyTail);
        ++_size;
    }
    
    public Item removeFirst()
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();   
        ListNode oldHead = _dummyHead.next;
        link(_dummyHead, oldHead.next);
        --_size;
        return oldHead.val;
    }
    
    public Item removeLast()
    {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        ListNode oldTail = _dummyTail.prev;
        link(oldTail.prev, _dummyTail);
        --_size;
        return oldTail.val;
    }
    
    public Iterator<Item> iterator()
    {
        return new MyIterator();
    }
    
    
    private class MyIterator implements Iterator<Item>
    {
        private ListNode current = _dummyHead.next;
        public void remove()
        {
            throw new java.lang.UnsupportedOperationException();
        }

        
        public boolean hasNext()
        {
            // implement
            return current != _dummyTail;
        }
        
        public Item next()
        {
            // implement
            if (!hasNext()) throw new java.util.NoSuchElementException();
            Item item = current.val;
            current = current.next;
            return item;
        }
        
    }
    
    
    
    public static void main(String[] args)
    {
        Deque<Integer> dq = new Deque<Integer>();
        StdOut.println(dq.isEmpty());
        dq.addFirst(1);
        dq.addFirst(2);
        dq.addLast(3);
        dq.addLast(4);
        dq.addFirst(5);
        dq.addLast(6);
        for(int n : dq)
        {
            StdOut.print(" " + n);
        }
        StdOut.println();
        StdOut.println("removed : " + dq.removeFirst());
        StdOut.println("removed : " + dq.removeLast());
        for(int n : dq)
        {
            StdOut.print(" " + n);
        }
        StdOut.println();
    }
    
}