import java.util.*;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdDraw;

public class FastCollinearPoints
{
    private final LineSegment[] _segment;
    
    public FastCollinearPoints(Point[] points)
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

        // calculate
        Map<Double, List<Point>> lines = new HashMap();
        List<LineSegment> result = new ArrayList();
        for(int i=0; i<=pnt.length - 4; ++i)
        {
            Point[] rest = Arrays.copyOfRange(pnt, i + 1, pnt.length);
            Arrays.sort(rest, pnt[i].slopeOrder());
            
            int cnt = 0;
            for(int j=0; j<rest.length; ++j)
            {
                ++cnt;
                double slp = pnt[i].slopeTo(rest[j]);
                if ( j == rest.length - 1 || slp != pnt[i].slopeTo(rest[j+1]))
                {
                    if(cnt >= 3) 
                    {
                        if(!lines.containsKey(slp))
                        {
                            result.add(new LineSegment(pnt[i], rest[j]));
                            List<Point> ls = new ArrayList();
                            ls.add(rest[j]);
                            lines.put(slp, ls);
                        }
                        else
                        {
                            if(!lines.get(slp).contains(rest[j]))
                            {
                                result.add(new LineSegment(pnt[i], rest[j]));
                                lines.get(slp).add(rest[j]);
                            }
                        }
                    }
                    cnt = 0;
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
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        
        for (LineSegment segment : collinear.segments()) 
        {
            StdOut.println(segment);
            segment.draw();
        }

        
    }
    
    
}