namespace Pathfinder
{
    class Point
    {
        public Point()
        {
        }

        public Point(int x, int y)
        {
            _x = x;
            _y = y;
        }

        int _x = 0;
        public int X
        {
            get { return _x; }
            set { _x = value; }
        }

        int _y = 0;
        private Point _from;
        public int Y
        {
            get { return _y; }
            set { _y = value; }
        }

        internal Point Add(Point _offset)
        {
            this.X += _offset.X;
            this.Y += _offset.Y;
            return this;
        }

        internal Point Subtract(Point _offset)
        {
            this.X -= _offset.X;
            this.Y -= _offset.Y;
            return this;
        }
    }
}
