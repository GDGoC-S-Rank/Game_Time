import "./Stage2.css";
import blackScreen from "../resources/images/black.png";
import hsBg from "../resources/images/hs/hbg.png";

// Heart Star
export function Stage2() {
  return (
    <div className="stage2-container">
      <img src={blackScreen} alt="screenArea" className="blackScreen" />
      {/* <img src={hsBg} alt="hsBg" className="hsBg" /> */}
    </div>
  );
}
