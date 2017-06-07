import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import java.util.Iterator;
import java.util.NoSuchElementException;


public class RandomizedQueue<Item> implements Iterable<Item>
{
    private Item[] _A;
    private int _N;
    private int _end;

    public RandomizedQueue()
    {
        _A = (Item[]) new Object[3];
        _N = 0;
        _end = 0;
    }
    
    
    public boolean isEmpty()
    {
        return _N == 0;
    }
    
    public int size()
    {
        return _N;
    }
    
    private void adjust()
    {
        _end = 0;
        for(int i=0; i<_A.length; ++i)
        {
            if(_A[i] != null) _A[_end++] = _A[i];
        }
        for(int i=_end; i<_A.length; ++i) _A[i] = null;
    }
    
    public void enqueue(Item item)
    {
        if(item == null) throw new java.lang.NullPointerException();
        
        if(_end == _A.length)
        {
            if(_N + _N <= _end) adjust();
            else expand(_A.length + _A.length);
        }
        
        _A[_end++] = item;
        
        ++_N;
        
    }
    
    private void expand(int newSize)
    {
        Item[] newA = (Item[]) new Object[newSize];
        _end = 0;
        for(int i=0; i<_A.length; ++i)
        {
            if(_A[i] != null) newA[_end++] = _A[i];
        }
        _A = newA;
    }

    
    private int select()
    {
        int i = 0;
        do
        {
            i = StdRandom.uniform(_A.length);
        }while(_A[i] == null);
        return i;
    }

    private void shrink(int newSize)
    {
        Item[] newA = (Item[]) new Object[newSize];
        _end = 0;
        for(int i=0; i<_A.length; ++i)
        {
            if(_A[i] != null) newA[_end++] = _A[i];
        }
        
        _A = newA;
    }

    public Item dequeue()
    {
        if(isEmpty()) throw new java.util.NoSuchElementException();
        if(_N == _A.length / 4) shrink(_A.length / 2);
        int ind = select();
        Item result = _A[ind];
        _A[ind] = null;
        --_N;
        return result;
    }
    
    public Item sample()
    {
        if(isEmpty()) throw new java.util.NoSuchElementException();
        return _A[select()];
    }
    
    public Iterator<Item> iterator()
    {
        return new MyIterator();
    }
    
    private class MyIterator implements Iterator<Item>
    {
        private Item[] a;
        private int current;
        
        public MyIterator()
        {
            a = (Item[]) new Object[_N];
            int ind = 0;
            for(int i=0; i<_A.length; ++i)
            {
                if(_A[i] != null)
                {
                    a[ind++] = _A[i];
                    if(ind == _N) break;
                }
            }
            StdRandom.shuffle(a);
            current = 0;
        }
        
        public void remove()
        {
            throw new java.lang.UnsupportedOperationException();
        }

        
        public boolean hasNext()
        {
            // implement
            return current != a.length;
        }
        
        public Item next()
        {
            // implement
            if (!hasNext()) throw new java.util.NoSuchElementException();
            return a[current++];
        }
        
    }
    
    
    public static void main(String[] args)
    {
        RandomizedQueue<Integer> rq = new RandomizedQueue<Integer>();
        rq.enqueue(1);
        rq.enqueue(2);
        rq.enqueue(3);
        rq.enqueue(4);
        StdOut.println("size : " + rq.size());
        for(int i=0;i<4;++i)
        {
            StdOut.print(" " + rq.dequeue());
        }
        StdOut.println();
        StdOut.println("size : " + rq.size());
        
    }
}