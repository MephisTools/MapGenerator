using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

namespace Pathfinder
{
    class Program
    {
        static void Main(string[] args)
        {
            StringBuilder map_m = new StringBuilder(99999);
            
            try
            {
                Init();
                GetMap(0x1B8E7001, 1, 1, map_m);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }

            string foo = map_m.ToString();
            List<string> lines = foo.Split('\n').ToList();

            char[,] map = new char[lines.Max(line => line.Length), lines.Count - 1];



            for (int lineIndex = 1; lineIndex < lines.Count; lineIndex++)
                for (int charIndex = 0; charIndex < lines[lineIndex].Length; charIndex++)
                    map[charIndex, lineIndex - 1] = lines[lineIndex][charIndex];

           // var origin = new Point(0, 0);
           Point origin = new Point(int.Parse(lines[0].Split(',')[0]), int.Parse(lines[0].Split(',')[1]));
           Pathfinder p = new Pathfinder(map, new Point(97,15), new Point(165,83), origin);
           List<Point> path = p.getPath();

            foreach (Point pt in path)
            {
                map[pt.X - origin.X, pt.Y - origin.Y] = 'o';
            }

            StringBuilder s = new StringBuilder(40000);
            for (int j = 0; j < map.GetLength(1); j++)
            {
                for (int i = 0; i < map.GetLength(0); i++)
                {
                    s.Append(map[i, j]);
                }
                s.Append("\r\n");
            }

            File.WriteAllText(@"path.txt", s.ToString()); 
            
        }
        //0x1B8E7001
        [System.Runtime.InteropServices.DllImport(@"\\VBOXSVR\vms\share\MapGenerator\ccmap\Debug\ccmap.dll",
                CharSet = CharSet.Ansi, 
                CallingConvention = CallingConvention.StdCall)]
        public static extern void GetMap(int seed, int act, int level, StringBuilder map);

        [System.Runtime.InteropServices.DllImport(@"\\VBOXSVR\vms\share\MapGenerator\ccmap\Debug\ccmap.dll",
                CharSet = CharSet.Ansi,
                CallingConvention = CallingConvention.StdCall)]
        public static extern void Init(); 
    }
}
