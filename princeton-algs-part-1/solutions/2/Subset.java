import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdOut;

public class Subset
{
    
    public static void main(String[] args)
    {
        int K = Integer.parseInt(args[0]);
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        for(int i=0; i<K; ++i)
        {
            String s = StdIn.readString();
            rq.enqueue(s);
        }
        
        int N = K;
        while(!StdIn.isEmpty())
        {
            String s = StdIn.readString();
            ++N;
            if(StdRandom.uniform(N) < K)
            {
                rq.dequeue();
                rq.enqueue(s);
            }
        }
        
        for(int i=0; i<K; ++i)
        {
            StdOut.println(rq.dequeue());
        }
    }
}