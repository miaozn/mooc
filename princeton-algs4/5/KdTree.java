import java.util.*;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.StdDraw;


public class KdTree
{
    private int _size;
    private Node _root;
    
    public KdTree()
    {
        _size = 0;
        _root = null;
    }

    private static class Node
    {
        public Point2D p;
        public RectHV rect;
        public Node lb; // left / bottom
        public Node rt; // right / top
        
        public Node(Point2D pn, RectHV re)
        {
            p = pn;
            rect = re;
            lb = null;
            rt = null;
        }
    }
    
    public boolean isEmpty()
    {
        return _size == 0;
    }
    
    public int size()
    {
        return _size;
    }
    
    public void insert(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();
        if(_root == null)
        {
            _root = new Node(p, new RectHV(0,0,1,1));
            ++_size;
            return;
        }
        
        if(!contains(p))
        {
            insert(_root, p, true);
            ++_size;
        }
    }
    
    
    private void insert(Node parent, Point2D p, boolean vertical)
    {
        if(vertical)
        {
            if(p.x() < parent.p.x())
            {
                // left
                if(parent.lb == null)
                {
                    parent.lb = new Node(p, new RectHV( parent.rect.xmin(), parent.rect.ymin(), parent.p.x(), parent.rect.ymax() ));
                }
                else
                {
                    insert(parent.lb, p, false);   
                }
            }
            else
            {
                if(parent.rt == null)
                {
                    parent.rt = new Node(p, new RectHV( parent.p.x(), parent.rect.ymin(), parent.rect.xmax(), parent.rect.ymax() ));
                }
                else
                {
                    insert(parent.rt, p, false);
                }
            }
        }
        else
        {
            if(p.y() < parent.p.y())
            {
                // bottom
                if(parent.lb == null)
                {
                    parent.lb = new Node(p, new RectHV( parent.rect.xmin(), parent.rect.ymin(), parent.rect.xmax(), parent.p.y() ));
                }
                else
                {
                    insert(parent.lb, p, true);
                }
            }
            else
            {
                if(parent.rt == null)
                {
                    parent.rt = new Node(p, new RectHV( parent.rect.xmin(), parent.p.y(), parent.rect.xmax(), parent.rect.ymax() ));
                }
                else
                {
                    insert(parent.rt, p, true);
                }
            }
        }
    }
    
    
    public boolean contains(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();
        if(_root == null) return false;
        
        return contains(_root, p, true);
    }
    
    
    private boolean contains(Node parent, Point2D p, boolean vertical)
    {
        if(parent == null) return false;
        if(parent.p.equals(p)) return true;
        if(vertical)
        {
            if(p.x() < parent.p.x()) return contains(parent.lb, p, false);
            else return contains(parent.rt, p, false);
        }
        
        // else
        if(p.y() < parent.p.y()) return contains(parent.lb, p, true);
        else return contains(parent.rt, p, true);
        
    }
    
    
    public void draw()
    {
        draw(_root, true);
    }
    
    
    private void draw(Node node, boolean vertical)
    {
        if(node == null) return;
        // point
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.setPenRadius(.01);

        if(vertical)
        {
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.setPenRadius();
            StdDraw.line(node.p.x(), node.rect.ymin(), node.p.x(), node.rect.ymax());
            draw(node.lb, false);
            draw(node.rt, false);
        }
        else
        {
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.setPenRadius();
            StdDraw.line(node.rect.xmin(), node.p.y(), node.rect.xmax(), node.p.y());
            draw(node.lb, true);
            draw(node.rt, true);
        }
    }
    
    public Iterable<Point2D> range(RectHV rect)
    {
        if(rect == null) throw new java.lang.NullPointerException();
        List<Point2D> result = new ArrayList();
        findInRange(result, _root, rect);
        return result;
    }
    
    private void findInRange(List<Point2D> result, Node node, RectHV rect)
    {
        if(node == null) return;
        if(rect.contains(node.p)) result.add(node.p);
        
        if(node.lb != null && node.lb.rect.intersects(rect))
        {
            findInRange(result, node.lb, rect);
        }
        if(node.rt != null && node.rt.rect.intersects(rect))
        {
            findInRange(result, node.rt, rect);
        }
    }


    private double _minSoFar;
    private Point2D _minP;
    public Point2D nearest(Point2D p)
    {
        if(p == null) throw new java.lang.NullPointerException();

        _minSoFar = Double.MAX_VALUE;
        _minP = null;
        findNearest(_root, p);
        
        return _minP;
    }
    
    private void findNearest(Node node, Point2D p)
    {
        if(node == null) return;

        double dist = node.rect.distanceSquaredTo(p);
        if(dist < _minSoFar)
        {
            dist = node.p.distanceSquaredTo(p);
            if(dist < _minSoFar)
            {
                _minSoFar = dist;
                _minP = node.p;
            }

            Node first = null;
            Node second = null;

            if(node.rt != null && node.rt.rect.contains(p))
            {
                first = node.rt;
                second = node.lb;
            }
            else
            {
                first = node.lb;
                second = node.rt;
            }
            findNearest(first, p);
            findNearest(second, p);

        }
        
    }
    
    public static void main(String[] args)
    {
        // implements..
    }
}