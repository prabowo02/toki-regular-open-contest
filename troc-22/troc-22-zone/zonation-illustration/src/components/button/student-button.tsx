import { Button } from 'react-bootstrap';
import {ReactComponent as Logo} from '../../assets/student-1.svg';
import { useZonation } from '../../provider/zonation-provider';
import './style.scss'

interface ButtonProps {
  studentId: number
}

function StudentButton({studentId}: ButtonProps) {
  const { activeStudent, changeActiveStudent } = useZonation();

  function handleClick() {
    changeActiveStudent(studentId)
  }

  return (
    <Button variant='secondary' className='button-wrapper' disabled={activeStudent.id === studentId} onClick={handleClick}>
      <Logo className='student' width='100%' height='100%' />
      <div className='student-name'>S{studentId}</div>
    </Button>
  )
}

export default StudentButton
