using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IvyyyAI
{
    public class IvyyySoldier : Soldier
    {
        bool m_deployed = false;

        public int Depth { get;set;}
        public bool Deployed => m_deployed;

        public void Deploy()
        {
            m_deployed = true;
        }

        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            //Target tower with least health first!
            targets.Sort((a, b) => a.Health.CompareTo(b.Health));
            return targets;
        }

        public override void Move()
        {
            //Auto deploy if tower in range
            //Prevents soldiers from being sniped in standby zone
            if (!Deployed && IsTowerInRange())
                m_deployed = true;

            if (speed > 0 && posY < PlayerLane.HEIGHT)
            {
                for (int i = speed; i > 0; i--)
                {
                    //Try to reach bottom row
                    if (Deployed)
                    {
                        IvyyyPosition waypoint = new();
                        waypoint.x = posX;
                        waypoint.y = posY + 1;
                        ApproachWaypoint(ref waypoint);
                    }
                    //Move until border of standby zone
                    else if (posY < Depth)
                        MoveTo(posX, PosY+1);
                }
            }
        }

        private void ApproachWaypoint (ref IvyyyPosition waypoint)
        {
            if (MoveTo(waypoint.x, waypoint.y)) return;
            if (MoveTo(waypoint.x + 1, waypoint.y)) return;
            if (MoveTo(waypoint.x - 1, waypoint.y)) return;
            if (MoveTo(waypoint.x + 1, PosY)) return;
            if (MoveTo(waypoint.x - 1, PosY)) return;
            if (MoveTo(waypoint.x, PosY - 1)) return;
            if (MoveTo(waypoint.x - 1, PosY - 1)) return;
            if (MoveTo(waypoint.x + 1, PosY - 1)) return;
        }

        private bool IsTowerInRange()
        {
            List<Tower> towers = new List<Tower>();

            for (int x = Math.Max(0, PosX - 2); x < Math.Min(7, PosX + 3); ++x)
            {
                for (int y = Math.Max(0, PosY); y < Math.Min(20, PosY + 3); ++y)
                {
                    Unit unit = player.EnemyLane.GetCellAt(x, y).Unit;

                    if (unit is Tower)
                        return true;
                }
            }

            return false;
        }
    }
}
