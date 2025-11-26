using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IvyyyAI
{
    //Implement a custom Tower for targeting
    //The defense stands and falls with the right targeting
    //Targeting the furthest tower with most hp proved to be superior
    public class IvyyyTower: Tower
    {
        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            targets.Sort((a, b) =>
            {
                float distA = GetDistance (a.PosX, a.PosY);
                float distB = GetDistance(b.PosX, b.PosY); 

                int distanceCompare = distA.CompareTo(distB);

                //Focus most further target first
                if (distanceCompare != 0)
                    return distanceCompare;

                //Focus target with most health first
                return a.Health.CompareTo(b.Health);
            });

            return targets;
        }

        private float GetDistance (int x, int y)
        {
            float xOffset = Math.Abs(x - this.PosX);
            float yOffset = Math.Abs(y - this.PosY);
            return (float)Math.Sqrt (Math.Pow(xOffset, 2.0) + Math.Pow(yOffset, 2.0));
        }
    }
}
