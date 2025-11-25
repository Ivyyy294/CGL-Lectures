using GameFramework;

namespace IvyyyAI
{
    public class IvyyyDeploySoldierRule : IvyyyRule
    {
        public IvyyyDeploySoldierRule(IvyyyWorldState state) : base(state)
        {
            m_target = "AttackLanes";
            m_weight = 10f;
            m_axis.Add(new IvyyyRuleAxis("LaneRowCounter", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 100f, 0f, 0f)));
            //m_axis.Add(new IvyyyRuleAxis("LaneDeploySoldier", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
            //m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.25f, 2f, 0.75f, 1f)));
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Deploy Soldier!");

            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            for (int x = 0; x < attackLane.Width; ++x)
            {
                int xPos = attackLane.StartIndex + x;
                for (int y = 0; y < attackLane.Depth; ++y)
                {
                    Unit unit = m_worldState.Player.EnemyLane.GetCellAt(xPos, y).Unit;

                    if (unit is IvyyySoldier)
                    {
                        IvyyySoldier soldier = unit as IvyyySoldier;
                        soldier.Deploy();
                    }
                }
            }

            m_worldState.RowCounter = 0;
        }
    }
}
