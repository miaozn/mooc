import java.util.*;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;
import edu.princeton.cs.algs4.StdDraw;

public class PointSET
{
    private SET<Point2D> _pnt;
    
    public PointSET()
    {
        _pnt = new SET();
    }
    
    public boolean isEmpty()
    {
        return _pnt.isEmpty();
    }
    
    public int size()
    {
        return _pnt.size();
    }
    
    public void insert(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();
        _pnt.add(p);
    }
    
    public boolean contains(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();
        return _pnt.contains(p);
    }
    
    public void draw()
    {
        for(Point2D p : _pnt) p.draw();   
    }
    
    public Iterable<Point2D> range(RectHV rect)
    {
        if(rect == null) throw new java.lang.NullPointerException();
        List<Point2D> result = new ArrayList();
        for(Point2D p : _pnt)
        {
            if(rect.contains(p)) result.add(p);
        }
        
        return result;
    }
    
    public Point2D nearest(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();
        double min = Double.MAX_VALUE;
        Point2D minP = null;
        for(Point2D that : _pnt)
        {
            double d = p.distanceSquaredTo(that);
            if(d < min)
            {
                min = d;
                minP = that;
            }
        }
        
        return minP;
    }
    
    public static void main(String[] args)
    {
        // implements..
    }
}