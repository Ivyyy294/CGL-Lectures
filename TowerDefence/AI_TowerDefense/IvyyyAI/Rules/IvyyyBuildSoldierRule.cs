using GameFramework;

namespace IvyyyAI
{
    public class IvyyyBuildSoldierRule : IvyyyRule
    {
        public IvyyyBuildSoldierRule(IvyyyWorldState state) : base(state)
        {
            m_weight = 5f;
            m_target = "AttackLanes";
            m_axis.Add(new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 4f, 0f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("CanBuySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 2f, 1f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("DeployTower", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 1f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerHp", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.25f, 2f, 0.75f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerInReach", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.05f, 2f, 0.95f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.2f, 2f, 1f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("LaneSuccessFactor", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.25f, 4f, 1f, 1f)));
        }

        public override void Action(object target)
        {
            if (m_worldState.ActionTyp != IvyyyPerception.ActionTyp.DeploySoldiers)
                return;

            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Soldier!");

            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            for (int i = 0; i < attackLane.Width; ++i)
            {
                int xPos = attackLane.StartIndex + i;
                m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos);
            }
        }
    }
}
