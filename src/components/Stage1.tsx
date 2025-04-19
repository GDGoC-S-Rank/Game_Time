import "./Stage1.css";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage from "../resources/images/startScene/bg.png";

// Start Scene(Space is key)
export function Stage1() {
  return (
    <div className="stage1-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={bgImage} alt="bg" className="bgImage" />
    </div>
  );
}
