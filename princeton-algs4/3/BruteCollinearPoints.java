import java.util.*;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;


public class BruteCollinearPoints
{

    private final LineSegment[] _segment;

    public BruteCollinearPoints(Point[] points)
    {
        if(null == points) throw new java.lang.NullPointerException();
        for(Point p : points)
        {
            if(null == p) throw new java.lang.NullPointerException();
        }
        
        Point[] pnt = Arrays.copyOf(points, points.length);
        
        Arrays.sort(pnt);
        for(int i=1; i<pnt.length; ++i)
        {
            if(pnt[i].compareTo(pnt[i-1]) == 0) throw new java.lang.IllegalArgumentException();
        }
        
        //calculate
        List<LineSegment> result = new ArrayList();
        for(int i=0; i<=pnt.length-4; ++i)
        {
            for(int j=i+1; j<=pnt.length-3; ++j)
            {
                for(int k=j+1; k<=pnt.length-2; ++k)
                {
                    for(int q=k+1; q<=pnt.length-1; ++q)
                    {
                        double s1 = pnt[i].slopeTo(pnt[j]);
                        double s2 = pnt[i].slopeTo(pnt[k]);
                        double s3 = pnt[i].slopeTo(pnt[q]);
                        if(s1 == s2 && s1 == s3) result.add(new LineSegment(pnt[i], pnt[q]));
                    }
                }
            }
        }
        
        _segment = new LineSegment[result.size()];
        result.toArray(_segment);


    }

    public int numberOfSegments()
    {
        return _segment.length;
    }
    
    public LineSegment[] segments()
    {
        return Arrays.copyOf(_segment, numberOfSegments());
    }

    public static void main(String[] args)
    {

        // read the N points from a file
        In in = new In(args[0]);
        int N = in.readInt();
        Point[] points = new Point[N];
        for (int i = 0; i < N; i++) 
        {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }


        // draw the points
        StdDraw.show(0);
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();



        // print and draw the line segments
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        
        for (LineSegment segment : collinear.segments()) 
        {
            StdOut.println(segment);
            segment.draw();
        }
        
        
    }

}