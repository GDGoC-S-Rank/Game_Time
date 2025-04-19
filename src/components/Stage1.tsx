import "./Stage1.css";
import bgImage from "../resources/images/startScene/bg.png";

// Start Scene(Space is key)
export function Stage1() {
  return (
    <div className="stage1-container">
      <img src={bgImage} alt="bg" className="bgImage" />
    </div>
  );
}
