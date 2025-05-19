import { useEffect } from "react";

// 지속시간이 짧은 키 이펙트 ✨
export function useKeyEffect(onKeyPress: (key: string) => void) {
  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (event.code === "Space" || event.code === "ArrowUp") {
        event.preventDefault(); // 🔴 기본 스크롤 동작 차단
        onKeyPress(event.code); // 눌린 키를 콜백으로 전달
      }
    };

    window.addEventListener("keydown", handleKeyDown);
    return () => window.removeEventListener("keydown", handleKeyDown);
  }, [onKeyPress]);
}

// **의존성 배열**입니다.
// `onSpacePress`가 바뀌면 useEffect 전체가 다시 실행되어 리스너도 재등록됩니다.
// 보통은 `useCallback`을 함께 사용해 불필요한 재실행을 막습니다.
