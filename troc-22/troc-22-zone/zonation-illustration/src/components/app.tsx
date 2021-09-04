import StudentButton from './button/student-button';
import ZonationProvider from '../provider/zonation-provider';
import './style.scss'
import ZonationMap from './map/map';
import ZonationLegend from './legend/legend';

function App() {
  return (
    <ZonationProvider>
      <ZonationMap />
      <div className='button-container'> 
        {[1, 2, 3, 4].map((id) => <StudentButton studentId={id} key={id}/>)}
      </div>
      <ZonationLegend />
    </ZonationProvider>
  )
}

export default App
