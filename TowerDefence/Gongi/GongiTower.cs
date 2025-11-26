using System;
using System.Collections.Generic;

namespace GameFramework
{

    /*
     * Automatically called by the game play. Forbidden to use as part of
     * the assignment.
     * 
     * A Tower is a non-movable unit. Towers are expensive, but crucial to prevent the
     * opponents soldiers to get through. Strategic placement of towers is crucial to success.
     * 
     */
    public class GongiTower : Tower
    {
        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            targets.Sort((a, b) =>
            {

                int distA = Math.Abs(a.PosX - this.PosX) + Math.Abs(a.PosY - this.PosY);
                int distB = Math.Abs(b.PosX - this.PosX) + Math.Abs(b.PosY - this.PosY);

                int distanceCompare = distA.CompareTo(distB);
                if (distanceCompare != 0)
                    return distanceCompare;

                return a.Health.CompareTo(b.Health);
            });

            return targets;
        }

    }
}