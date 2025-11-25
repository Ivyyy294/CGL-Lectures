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
            if (speed > 0 && posY < PlayerLane.HEIGHT)
            {
                for (int i = speed; i > 0; i--)
                {
                    IvyyyPosition waypoint = new();
                    waypoint.x = posX;
                    waypoint.y = posY;

                    if (Deployed || posY < Depth)
                        waypoint.y = posY + 1;
                    
                    ApproachWaypoint(ref waypoint);
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
    }
}
