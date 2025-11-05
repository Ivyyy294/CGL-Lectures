using GameFramework;

namespace IvyyyAI
{
    public class TowerDefensePerception
    {
        public enum ActionTyp
        {
            TurnStart,
            TurnEnd,
            DeployTowers,
            DeploySoldiers
        }

        public Player Player { get; set; }
        public ActionTyp CurrentActionTyp { get; set; }
    }
}
