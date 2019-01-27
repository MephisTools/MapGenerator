using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Pathfinder
{
    class Pathfinder
    {
        Point[] _movements;

        List<Point> _path = new List<Point>();
        
        public List<Point> getPath()
        {
            Pathfind();
            HighlightPath();
            return _path;
        }

        int[,] _steps = null;
        public int[,] Steps
        {
            get { return _steps; }
            set { _steps = value; }
        }

        char[,] _map = null;
        public char[,] Map
        {
            get { return _map; }
            set { _map = value; }
        }

        Point _to = null;
        public Point To
        {
            get { return _to; }
            set { _to = value; }
        }

        Point _from = null;
        public Point From
        {
            get { return _from; }
            set { _from = value; }
        }

        Point _offset = null;
        public Point Offset
        {
            get { return _offset; }
            set { _offset = value; }
        }

        public Pathfinder(char[,] map, Point to, Point from, Point offset)
        {
            _map = map;
            _offset = offset;
            _steps = new int[map.GetLength(0), map.GetLength(1)];

            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    _steps[i, j] = 10000;
                }
            }

            _to = to;
            _from = from;
            InitMovements();
        }

        public void InitMovements()
        {
            _movements = new Point[]
            {
                new Point(-1, -1),
                new Point(0, -2),
                new Point(1, -1),
                new Point(2, 0),
                new Point(1, 1),
                new Point(0, 2),
                new Point(-1, 1),
                new Point(-2, 0)
            };
        }

        public void Pathfind()
        {
            Point startingPoint = new Point(_to.X, _to.Y);
            startingPoint.Subtract(_offset);

            _steps[startingPoint.X, startingPoint.Y] = 0;

            while (true)
            {
                bool madeProgress = false;


                for (int x = 0; x < _steps.GetLength(0); x++)
                {
                    for (int y = 0; y < _steps.GetLength(1); y++)
                    {
                        if (LocationOpen(x, y))
                        {
                            int passHere = _steps[x, y];

                            foreach (Point movePoint in ValidMoves(x, y))
                            {
                                int newX = movePoint.X;
                                int newY = movePoint.Y;
                                int newPass = passHere + 1;

                                if (_steps[newX, newY] > newPass)
                                {
                                    _steps[newX, newY] = newPass;
                                    madeProgress = true;
                                }
                            }
                        }
                    }
                }

                if (!madeProgress)
                {
                    break;
                }
            }
        }

        private bool LocationOpen(int x, int y)
        {
            switch (_map[x, y])
            {
                case 'X':
                    return false;
                default:
                    return true;
                /*case '\0':
                case ' ':
                case 'U':
                    return true;
                
                default:
                    return false;*/
            }
        }

        public void HighlightPath()
        {
            /*
             * 
             * Mark the path from monster to hero.
             * 
             * */
            Point startingPoint = new Point(_from.X, _from.Y);
            startingPoint.Subtract(_offset);
            int pointX = startingPoint.X;
            int pointY = startingPoint.Y;
            if (pointX == -1 && pointY == -1)
            {
                return;
            }

            while (true)
            {
                Point lowestPoint = new Point(0, 0);
                int lowest = 10000;

                foreach (Point movePoint in ValidMoves(pointX, pointY))
                {
                    int count = _steps[movePoint.X, movePoint.Y];
                    if (count < lowest)
                    {
                        lowest = count;
                        lowestPoint.X = movePoint.X;
                        lowestPoint.Y = movePoint.Y;
                    }
                }
                if (lowest != 10000)
                {
                    _path.Add(new Point(lowestPoint.X + _offset.X, lowestPoint.Y + _offset.Y));
                    pointX = lowestPoint.X;
                    pointY = lowestPoint.Y;
                }
                else
                {
                    break;
                }

                if (pointX + _offset.X == _to.X && pointY + _offset.Y == _to.Y)
                {
                    break;
                }
            }
        }

        private IEnumerable<Point> ValidMoves(int x, int y)
        {
            foreach (Point movePoint in _movements)
            {
                int newX = x + movePoint.X;
                int newY = y + movePoint.Y;

                if (ValidCoordinates(newX, newY) &&
                    LocationOpen(newX, newY))
                {
                    yield return new Point(newX, newY);
                }
            }
        }

        private bool ValidCoordinates(int newX, int newY)
        {
            if (_map.GetLength(0) > newX && _map.GetLength(1) > newY && newX >= 0 && newY >= 0)
            {
                return true;
            }
            return false;
        }
    }
}
