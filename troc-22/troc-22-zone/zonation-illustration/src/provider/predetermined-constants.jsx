export const studentReachability = {
  0: [0, 0, 0, 0, 0],
  1: [0, 0, 0, 1, 1],
  2: [0, 0, 0, 1, 1],
  3: [0, 1, 1, 1, 1],
  4: [0, 0, 1, 0, 0],
}

export const studentLocation = [0, 4, 3, 4, 2]
export const studentEnrolledSchool = [0, 3, 3, 1, 2]

export const studentMessage = {
  0: 'Please select a student to view the status.',
  1: 'Student 1 lived in junction 4 and can enroll in school 3 and 4.',
  2: 'Student 2 lived in junction 3 and can enroll in school 3 and 4.',
  3: 'Student 3 lived in junction 4 and can enroll in school 1, 2, 3, and 4.',
  4: 'Student 4 lived in junction 2 and can enroll in school 2.',
}

export default function getStudent(id) {
  return {
    id: id,
    enrolled: studentEnrolledSchool[id],
    location: studentLocation[id],
    message: studentMessage[id],
    canReach: studentReachability[id],
  }
}