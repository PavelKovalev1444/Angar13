coordsForSeemX(coords, distance, q0, q1, q2) {
  // 1 2 0
  const y = (coords[q1].y**2 - coords[q0].y**2 + distance[q0]**2 - distance[q1]**2) / (2 * (coords[q1].y - coords[q0].y))
  const xs = []
  xs.push(coords[q0].x + Math.sqrt(Math.abs(distance[q0]**2 - (y - coords[q0].y)**2)))
  xs.push(coords[q0].x - Math.sqrt(Math.abs(distance[q0]**2 - (y - coords[q0].y)**2)))
  let answer = null
  if (q2) {
    const forX1 = Math.abs((xs[0] - coords[q2].x)**2 + (y - coords[q2].y)**2 - distance[q2]**2)
    const forX2 = Math.abs((xs[1] - coords[q2].x)**2 + (y - coords[q2].y)**2 - distance[q2]**2)
    if (forX1 - forX2 > 0) {
      answer = { x: xs[1], y }
    } else {
      answer = { x: xs[0], y }
    }
  } else {
    if (Math.abs(xs[0]) <= 54) {
      answer = { x: xs[0], y }
    } else {
      answer = { x: xs[1], y }
    }
  }
  return answer
}