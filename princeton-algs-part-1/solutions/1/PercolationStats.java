import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;


public class PercolationStats
{
	private double[] threshold;

	public PercolationStats(int N, int T)
	{
		if(N <= 0 || T <= 0)
		{
			throw new java.lang.IllegalArgumentException();
		}

		threshold = new double[T];
		for(int i=0; i<T; ++i)
		{
			Percolation perc = new Percolation(N);
			int cnt = 0;
			int x = 1;
			int y = 1;
			while(!perc.percolates())
			{
				x = StdRandom.uniform(1, 1 + N);
				y = StdRandom.uniform(1, 1 + N);
				if(perc.isOpen(x, y)) continue;
				++cnt;
				perc.open(x, y);
			}
			threshold[i] = cnt*1.0/(N*N);
		}

	}

	public double mean()
	{
		return StdStats.mean(threshold);
	}

	public double stddev()
	{
		return StdStats.stddev(threshold);
	}


	private double halfInterval()
	{
		return 1.96 * stddev() / Math.sqrt(threshold.length);	
	}

	public double confidenceLo()
	{
		return mean() - halfInterval();
	}

	public double confidenceHi()
	{
		return mean() + halfInterval();
	}


	public static void main(String[] args)
	{

		PercolationStats ps = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));

		System.out.println("mean\t\t\t= " + ps.mean());
		System.out.println("stddev\t\t\t= " + ps.stddev());
		System.out.println("95% confidence interval\t= " + ps.confidenceLo() + ", " + ps.confidenceHi());
	}

}