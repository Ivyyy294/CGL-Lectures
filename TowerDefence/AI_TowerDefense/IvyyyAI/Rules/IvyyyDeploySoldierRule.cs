using GameFramework;

namespace IvyyyAI
{
    public class IvyyyDeploySoldierRule : IvyyyRule
    {
        public IvyyyDeploySoldierRule(TowerDefenseAgentState state) : base(state)
        {
            m_target = "AttackLanes";
            m_weight = 10f;
            m_axis.Add(new IvyyyRuleAxis("LaneDeploySoldier", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
            m_axis.Add(new IvyyyRuleAxis("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
        }

        public override void Action(object target)
        {
            int deployed = 0;

            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Deploy Soldier!");

            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            for (int x = 0; x < attackLane.Width; ++x)
            {
                int xPos = attackLane.StartIndex + x;
                for (int y = 0; y < 3; ++y)
                {
                    Unit unit = m_worldState.Player.EnemyLane.GetCellAt(xPos, y).Unit;

                    if (unit is IvyyySoldier)
                    {
                        IvyyySoldier soldier = unit as IvyyySoldier;
                        soldier.Deploy();
                        deployed++;
                    }
                }
            }
        }
    }
}
