import "./Stage6.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import bgImage1 from "../resources/images/spike/bg1.png";
import bgImage2 from "../resources/images/spike/bg2.png";
import bgImage3 from "../resources/images/spike/bg3.png";
import bgImage4 from "../resources/images/spike/bg4.png";
import control_panel from "../resources/images/fontImg/24.png";
import control_1p from "../resources/images/fontImg/23.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Spikes tend to kill you
export function Stage6() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    }
  });

  return (
    <div className="stage6-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_panel}
        alt="control_panel"
        className="stage6_control_panel"
      />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage6_control_1p ${isVisible_1p ? "visible" : ""}`}
      />

      <img src={bgImage1} alt="bg1" className="stage6-bgImage1" />
      {/* <img src={bgImage1} alt="bg2" className="stage6-bgImage2" />
      <img src={bgImage1} alt="bg3" className="stage6-bgImage3" />
      <img src={bgImage1} alt="bg4" className="stage6-bgImage4" /> */}
    </div>
  );
}
