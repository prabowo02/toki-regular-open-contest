import React from 'react'
import { useZonation } from '../../provider/zonation-provider'
import ZonationCanvas from './canvas'
import './style.scss'

function ZonationMap() {
  const { activeStudent } = useZonation();
  return (
    <>
      <div className='message-container'>
        {activeStudent.message}
      </div>
      <div className='canvas-container'>
        <ZonationCanvas />
      </div>
    </>
  )
}

export default ZonationMap
